net = require('net')
ffi = require('ffi')
libastar = ffi.Library('../lib/libastar', {
  'load_map': ['int', ['string']],
  'simpleAstar': ['int', [ 'int', 'int', 'int', 'int']]
})

startX = 1
startY = 1
endX   = 2
endY   = 2
file   = "../inp/map"

libastar.load_map file

server = net.createServer((newSocket) ->)

server.on('connection', (con)->
  con.on('data', (d)->
    console.log(d + "\n")
    #console.log libstar
    #libastar.simpleAstar(startX, startY, endX, endY)
    #console.log 'aaaaaaaaa'
  )
)

server.listen(8888, '127.0.0.1')
