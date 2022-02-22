//
// Created by david on 15-4-19.
//

#include "AssembleConnection.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <wait.h>

#define READ_PIPE 0
#define WRITE_PIPE 1

AssembleConnection::AssembleConnection()
    : m_valid(false), m_mainToChild{0}, m_childToMain{0}, m_input(nullptr), m_pid(0)
{
}

AssembleConnection::~AssembleConnection()
{
    Exit();
}

void AssembleConnection::StartAssembler(std::string asmFile)
{
    if (m_pid != 0)
    {
        Exit();
    }

    if (pipe(m_mainToChild) == -1)
    {
        std::cerr << "Failed to create pipe (P->C)" << std::endl;
        return;
    }

    if (pipe(m_childToMain) == -1)
    {
        std::cerr << "Failed to create pipe (C->P)" << std::endl;
        return;
    }

    m_pid = fork();
    if (m_pid == 0)
    {
        // Forked process
        close(m_childToMain[READ_PIPE]);
        close(m_mainToChild[WRITE_PIPE]);

        if (dup2(m_mainToChild[READ_PIPE], STDIN_FILENO) == -1)
        {
            std::cerr << "Failed to replcae COUT with pipe" << std::endl;
        }

        if (dup2(m_childToMain[WRITE_PIPE], STDOUT_FILENO) == -1)
        {
            std::cerr << "Failed to replcae COUT with pipe" << std::endl;
        }

        execl("./run", "", "-s", asmFile.c_str(), NULL);
    }
    else if (m_pid > 0)
    {
        // Main process
        close(m_mainToChild[READ_PIPE]);
        close(m_childToMain[WRITE_PIPE]);

        m_fbIn = new __gnu_cxx::stdio_filebuf<char>(m_childToMain[READ_PIPE], std::ios::in);
        m_input = new std::istream(m_fbIn);

        m_fbOut = new __gnu_cxx::stdio_filebuf<char>(m_mainToChild[WRITE_PIPE], std::ios::out);
        m_output = new std::ostream(m_fbOut);

        m_valid = true;
    }
    else
    {
        close(m_mainToChild[READ_PIPE]);
        close(m_mainToChild[WRITE_PIPE]);
        close(m_childToMain[READ_PIPE]);
        close(m_childToMain[WRITE_PIPE]);

        // Fork failed
        std::cerr << "Failed to fork" << std::endl;
    }
}

std::vector<int> AssembleConnection::Execute(int *data, int size)
{
    std::vector<int> outputs;

    if (!m_valid)
        return outputs;

    if (!Upload(data, size))
        return outputs;

    outputs = Download();

    (*m_output) << "NEXT" << std::endl;
    m_input->clear();
    m_input->ignore(100, '\n');
    return outputs;
}

std::string AssembleConnection::GetFeedback()
{
    std::string feedback;
    std::string buffer;

    if (m_valid)
    {
        return "No syntax error, did you meet all requirements? \r\n"
               "Do you have enough outputs?";
    }

    if (m_input == nullptr)
        return "";

    while (!m_input->eof())
    {
        std::getline(*m_input, buffer);
        feedback += buffer + "\r\n";
    }
    return feedback;
}

bool AssembleConnection::Upload(const int *data, int size)
{
    std::string response;

    for (int i = 0; i < size; ++i)
    {
        (*m_output) << std::to_string(data[i]) << std::endl;
    }
    (*m_output) << "-" << std::endl;

    (*m_input) >> response;
    if (response == "ERROR")
    {
        std::cerr << "Assemble returned error" << std::endl;

        m_valid = false;
        return false;
    }

    return true;
}

std::vector<int> AssembleConnection::Download() const
{
    std::vector<int> outputs;
    int output;

    do
    {
        (*m_input) >> output;

        if (m_input->fail())
            break;

        outputs.push_back(output);
    } while (true);

    return outputs;
}

void AssembleConnection::Exit()
{ // Skip params
    int status;

    if (m_pid == 0)
        return;
    //    (*m_output) << "-" << std::endl;
    //
    //    // Request close (everything except 'NEXT' will close
    //    (*m_output) << "-" << std::endl;

    close(m_mainToChild[READ_PIPE]);
    close(m_mainToChild[WRITE_PIPE]);
    close(m_childToMain[READ_PIPE]);
    close(m_childToMain[WRITE_PIPE]);

    delete m_output;
    delete m_input;

    kill(m_pid, 9);
    waitpid(m_pid, &status, 0);
    m_pid = 0;
}