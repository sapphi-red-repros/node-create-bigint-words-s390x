var binding = require('../index.js')
console.assert(binding.getFromI64() === 1234n)
console.assert(binding.getFromWords1() === 1234n)
console.assert(binding.getFromWords2() === 104740612850522834076882n)
