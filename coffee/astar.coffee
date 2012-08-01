ffi = require('ffi')
#ref = require('ref')

libastar = ffi.Library('../lib/libastar', {
  'simpleAstar': [ 'int', ['int', 'int', 'int', 'int'] ],
  'load_map': [ 'int', ['string'] ],
  'destroy_map': [ 'int', [] ],
})

#fd = './inp/inp.txt'
console.log 'before linking dynamic library ********'
if process.argv.length < 7
  console.log 'Usage: ' + process.argv[0] + ' ' + process.argv[1] + ' <map file> <startX> <startY> <endX> <endY>'
  process.exit

argvs = process.argv
libastar.load_map argvs[2]

libastar.simpleAstar parseInt(argvs[3]), parseInt(argvs[4]), parseInt(argvs[5]), parseInt(argvs[6])
libastar.simpleAstar 1, 1, 2, 3
libastar.destroy_map
console.log 'after linking dynamic library ********'
