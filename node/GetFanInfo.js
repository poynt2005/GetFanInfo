var nativeBinding = require("./GetFanInfo.node");

/**
 * Get the infomation of fans which are installed in your own computer
 * @returns { Object } - An object shows which fan you installed in your own computer, and their status
 */
var GetFanInfo = function () {
  return nativeBinding.GetFanInfo();
};

module.exports = GetFanInfo;
