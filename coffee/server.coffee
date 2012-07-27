net = require('net')
ffi = require('ffi')
libstar = ffi.Library('./libastar', {
  'simpleAstar': ['int', ['string', 'int', 'int', 'int', 'int']]
})

startX = 1
startY = 1
endX   = 2
endY   = 2
file   = "inp/inp.txt"

server = net.createServer((newSocket) ->)

server.on('connection', (con)->
  con.on('data', (d)->
    console.log(d + "\n")
    #console.log libstar
    libstar.simpleAstar(file, startX, startY, endX, endY)
    #console.log 'aaaaaaaaa'
  )
)

server.listen(8888, '127.0.0.1')
