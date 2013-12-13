$(document).ready(function () {

  var $onBtn = $("#on");
  var $offBtn = $("#off");

  function setDigitalPin(pin, value) {
    $.ajax({
      type: "POST",
      url: "/arduino/digital/" + pin + "/" + value,
      dataType: "json"
    });
  }

  $onBtn.on('click', function (e) {
    setDigitalPin(13, 1);
  });

  $offBtn.on('click', function (e) {
    setDigitalPin(13, 0);
  });

});
