const { defaults } = require('jest-config')

module.exports = {
  ...defaults,
  moduleFileExtensions: ['js'],
  testPathIgnorePatterns: ['<rootDir>/android/', '<rootDir>/ios/', '<rootDir>/node_modules/'],
}
