const socket = new WebSocket("ws://192.168.4.1:81/");
const frente = document.querySelector("#frente");
const tras = document.querySelector("#tras");
const gdir = document.querySelector("#gdir");
const gesq = document.querySelector("#gesq");

socket.addEventListener('open', (event) => {
    console.log('Conexão WebSocket aberta');      
});

//touchstarts

frente.addEventListener('touchstart', () => {
     socket.send('frente');
});

tras.addEventListener('touchstart', () => {
    socket.send('tras');
});

gdir.addEventListener('touchstart', () => {
    socket.send('gdir');
});

gesq.addEventListener('touchstart', () => {
    socket.send('gesq');
});

//touchends

frente.addEventListener('touchend', () => {
     socket.send('parado');
});

gdir.addEventListener('touchend', () => {
    socket.send('parado');
});

gesq.addEventListener('touchend', () => {
    socket.send('parado');
});

tras.addEventListener('touchend', () => {
    socket.send('parado');
});


