winston = require 'winston'
net = require 'net'
redis = require 'redis'
underscore = require 'underscore'
#fibonacci = require '../lib/fib'
fs = require 'fs'
os = require 'os'

ffi = require 'ffi'
libastar = ffi.Library('../lib/libastar', {
  'load_map': ['int', ['string']],
  'simpleAstar': ['int', ['int', 'int', 'int', 'int']],
  'destroy_map': ['int', []]
})
file = '../inp/map'

#customizing winston
winston.add winston.transports.File, { filename: '../log/hero_server.log' }
winston.remove winston.transports.Console


class TcpServer 
  constructor: (port, fibNum, mapfile)->
    @port = port
    @fibNum = fibNum
    @map = mapfile
    @redisClient = redis.createClient()
    #@tcpServer = net.createServer({allowHalfOpen:true})
    @tcpServer = net.createServer({allowHalfOpen:false})
    libastar.load_map @map

  start: ->
    @tcpServer.listen @port
    @serverHandler()
    @redisHandler()
    #@monitorServer()

  socketHandler: (socket)->
    socket.on 'connect', ->
      #winston.log 'info', 'socket connected'
    socket.on 'data', (data)=>
      #parsing data from clients
      datastr = data.toString()
      datastr = datastr.substr 0, datastr.length - 1
      #winston.log 'info', datastr
      #cpu-intensive calculation
      times = @fibNum
      for i in [1..times]
        #fibonacci.fib i
        libastar.simpleAstar(1, 1, 30, 35)
      #write data to redis
      #redisClient.set datastr, datastr, redis.print
      socket.write 'data covered'
    socket.on 'end', ->
      winston.log 'info', 'socket disconnected'

  serverHandler: ->
    #tcp server event handling
    #tcp server have the events below
    #listening #connection #close #error
    @tcpServer.on 'listening', ->
      winston.log 'info', 'TCP server listened'
    @tcpServer.on 'connection', (socket)=>
      #winston.log 'info', 'TCP server connected'
      @socketHandler(socket)
      socket.pipe socket
    @tcpServer.on 'close', ->
      winston.log 'info', 'TCP server closed'
      libastar.destroy_map()
    @tcpServer.on 'error', (err) =>
      if err.code == 'EADDRINUSE'
        winston.log 'error', 'Address in use, retrying ...'
        setTimeout =>
          tcpServer.close()
          tcpServer.listen(@port)
        , 10000
      else winston.log 'error', 'Error: ' + err

  redisHandler: ->
    @redisClient.on 'ready', ->
      winston.log 'info', 'redis client is ready'
    @redisClient.on 'connect', ->
      #redisClient.set 'hello1', 'world1', redis.print
      #redisClient.get 'hello1', redis.print
    @redisClient.on 'error', (err) ->
      winston.log 'error', 'Error' + err

  monitorServer: ->
    #print out profiling data repeatedly
    totalmem = os.totalmem()
    freemem = os.freemem()
    memratio = 1 - freemem/totalmem
    v8mem = process.memoryUsage()
    v8total = v8mem.heapTotal
    v8used = v8mem.heapUsed
    avgload = os.loadavg()
    console.log 'v8total\t\t\tv8mem_ratio\t\t\tosmem_ratio\t\t\tavgload1\t\t\tavgload5\t\t\tavgload15'
    setInterval(->
      freemem = os.freemem()
      memratio = 1 - freemem/totalmem
      v8mem = process.memoryUsage()
      v8total = v8mem.heapTotal
      v8used = v8mem.heapUsed
      v8ratio = v8used/v8total
      avgload = os.loadavg()
      console.log '%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d',v8total, v8ratio, memratio, avgload[0], avgload[1], avgload[2]
    ,1000)


tcpServer = new TcpServer(1234, 1, "../inp/map").start()
