$(document).ready(function () {

  var $servo1Angle = $("#servo1Angle");
  var $servo2Angle = $("#servo2Angle");

  // POST data needs to be included in the url string since bridge
  // does not currently parse the request body for data
  function setServoAngle(id, angle) {
    var request = $.ajax({
      type: "POST",
      url: "/arduino/servos/" + id + "/angle/" + angle
    });

    request.done(function (msg) {
      console.log(msg);
    });

    request.fail(function (jqXHR, textStatus) {
      console.log("Request failed: " + textStatus);
    });
  }

  $servo1Angle.on('change', function (e) {
    setServoAngle(1, $(this).val());
  });

  $servo2Angle.on('change', function (e) {
    setServoAngle(2, $(this).val());
  });

});
