import web_io from "../sockets/web-socket.js";
import fs, { link } from "fs";
import path from "path";
import { fileURLToPath } from 'url';
import { dirname } from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

export function create_game(uid, data) {
    let game_list = get_game_list();

    if (uid in game_list) {
        delete_game(uid);
    }
    game_list[uid] = data;

    fs.writeFileSync(path.resolve(__dirname, "game_list.json"), JSON.stringify(game_list), 'utf8', (err) => {
        if (err) {
            console.log("File error: ", err);
        }
        console.log("Game Added");
    });

    web_io.emit("game_list_res", game_list);
}

export function delete_game(uid) {
    let game_list = get_game_list();

    if (uid in game_list) {
        delete game_list[uid];
    }

    fs.writeFileSync(path.resolve(__dirname, "game_list.json"), JSON.stringify(game_list), 'utf8', (err) => {
        if (err) {
            console.log("File error: ", err);
        }
        console.log("Game Removed");
    });

    web_io.emit("game_list_res", game_list);
}

/**
 * Get formatted game list
 * 
 * @returns Game list json object
 */
export function get_game_list() {
    let return_data = {};
	let json_data = fs.readFileSync(path.resolve(__dirname, "game_list.json"), "utf-8");
    return_data = JSON.parse(json_data);

    return return_data;
}