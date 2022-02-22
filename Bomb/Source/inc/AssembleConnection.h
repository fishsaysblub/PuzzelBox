//
// Created by david on 15-4-19.
//

#ifndef MAIN_BOM_ASSEMBLECONNECTION_H
#define MAIN_BOM_ASSEMBLECONNECTION_H

#include <string>
#include <vector>
#include <ext/stdio_filebuf.h>

class AssembleConnection
{
public:
    explicit AssembleConnection();
    ~AssembleConnection();

public:
    void StartAssembler(std::string asmFile);
    std::vector<int> Execute(int data[], int size);
    std::string GetFeedback();

private:
    bool m_valid;
    int m_mainToChild[2];
    int m_childToMain[2];

    __gnu_cxx::stdio_filebuf<char> *m_fbIn;
    std::istream *m_input;

    __gnu_cxx::stdio_filebuf<char> *m_fbOut;
    std::ostream *m_output;
    pid_t m_pid;

private:
    bool Upload(const int *data, int size);
    std::vector<int> Download() const;

    void Exit();
};

#endif // MAIN_BOM_ASSEMBLECONNECTION_H
