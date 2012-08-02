net = require('net')

host = '127.0.0.1'
port = 8888

clientNum = 1000

socket = net.connect(port, host)
socket.on('connect', ->
  for i in [1..10000]
    socket.write('a')
)
