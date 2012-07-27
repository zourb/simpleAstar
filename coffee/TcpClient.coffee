net = require 'net'
winston = require 'winston'
winston.add winston.transports.File, { filename: '../log/hero_client.log' }
winston.remove winston.transports.Console


class TcpClient 
  constructor: (host, port)->
    @tcpClient  = net.connect host, port 
    @lasttime = 0
    @curtime = 0
    @status = 'initialized'

  #tcpclient startup
  start: (callback)->
    @clientHandler()
    callback?(@status)
  clientHandler: ->
    #socket event handling
    @tcpClient.on 'connect', =>
      winston.log 'info', 'tcp client connected'
      @curtime = new Date().getMilliseconds() 
      #write a random number between 1 and 1000
      @tcpClient.write Math.floor(Math.random()*1000) + '\n'
      @status = 'connected'
    @tcpClient.on 'data', (data)=>
      @lasttime = @curtime
      @curtime = new Date().getMilliseconds() 
      console.log @curtime - @lasttime
      winston.log 'info', data.toString()
      @tcpClient.write Math.floor(Math.random()*1000) + '\n'
      @status = 'received'
    @tcpClient.on 'end', ()->
      winston.log 'info', 'tcp client disconnected'
      @status = 'ended'
    @tcpClient.on 'error', (err)->
      winston.log 'error', 'tcp client error' + err
      @status = 'errored'
    @tcpClient.on 'close', ->
      winston.log 'info', 'tcp client closed'
      @status = 'closed'
#for i in [1..1]
new TcpClient(1234, '127.0.0.1').start()

module.exports = TcpClient
