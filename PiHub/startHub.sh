#!/bin/bash

# Start Socket-Server
( node ./socketcom/server/socket-server.js & )
echo "[Info] > Started Socket-Server";

# Start dashboard
( cd ./boxnet-admin && (npm run serve &) )
echo "[Info] > Started Dashboard";

#* Start Test Clients
( ./socketcom/client/startDummies.sh &)
echo "[Info] > Started Test Clients";