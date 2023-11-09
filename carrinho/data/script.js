const socket = new WebSocket('ws://10.93.0.219:81');
const btn = document.querySelector("#btn");

// Evento chamado quando a conexão WebSocket é aberta
socket.addEventListener('open', (event) => {
    console.log('Conexão WebSocket aberta');
            
    // Envia uma mensagem para o servidor quando a conexão é aberta
    socket.send('Olá, servidor!');
});

// Evento chamado quando uma mensagem é recebida do servidor
socket.addEventListener('message', (event) => {
    console.log('Mensagem recebida do servidor:', event.data);
});

// Adiciona um ouvinte de evento ao botão
btn.addEventListener('click', () => {
    // Envia uma mensagem para o servidor quando o botão é pressionado
    socket.send('frente');
});
