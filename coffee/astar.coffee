ffi = require('ffi')
#ref = require('ref')

libastar = ffi.Library('../lib/libastar', {
  'simpleAstar': [ 'int', ['string', 'int', 'int', 'int', 'int'] ]
})

#fd = './inp/inp.txt'
console.log 'before linking dynamic library ********'
if process.argv.length < 7
  console.log 'Usage: ' + process.argv[0] + ' ' + process.argv[1] + ' <input file> <startX> <startY> <endX> <endY>'
  process.exit()

argvs = process.argv
libastar.simpleAstar argvs[2], parseInt(argvs[3]), parseInt(argvs[4]), parseInt(argvs[5]), parseInt(argvs[6])
libastar.simpleAstar './inp/inp.txt', 1, 1, 2, 2
  #console.log 'linking successfully'
console.log 'after linking dynamic library ********'
