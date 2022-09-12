const http = require('http');
const express = require('express');
const path = require("path");

const app = express();

app.get('/', (req, res) =>{
    res.sendFile(path.join(__dirname, 'index.html'));
})

const server = http.createServer(app);

server.listen(8080,'localhost');