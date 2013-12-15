$(document).ready(function () {

  var $onBtn = $("#on");
  var $offBtn = $("#off");

  // POST data needs to be included in the url string since bridge
  // does not currently parse the request body for data
  function setDigitalPin(pin, value) {
    var request = $.ajax({
      type: "POST",
      url: "/arduino/digital/" + pin + "/" + value,
    });

    request.done(function (msg) {
      console.log(msg);
    });

    request.fail(function (jqXHR, textStatus) {
      console.log("Request failed: " + textStatus);
    });
  }

  $onBtn.on('click', function (e) {
    setDigitalPin(13, 1);
  });

  $offBtn.on('click', function (e) {
    setDigitalPin(13, 0);
  });

});
