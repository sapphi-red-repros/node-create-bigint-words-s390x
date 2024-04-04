var binding = require('../index.js')
console.log('getFromI64', binding.getFromI64() === 1234n)
console.log('getFromWords1',binding.getFromWords1() === 1234n)
console.log('getFromWords2',binding.getFromWords2() === 104740612850522834076882n)
