var path = require("path");
var getFanInfoLib = path
  .resolve("../GetFanInfo.lib")
  .replace(/\\/gm, "\\\\");


module.exports = {
    getFanInfoLib: getFanInfoLib
};
