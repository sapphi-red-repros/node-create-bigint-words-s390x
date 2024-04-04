const path = require('path')
const modulePath = path.join(__dirname, 'build', 'Release', 'binding.node')
module.exports = require(modulePath)
