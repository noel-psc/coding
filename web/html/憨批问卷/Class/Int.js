var numInput = document.getElementById("numInput");
submit.onclick = function() {
	var n = numInput.value;
	if (n > 0)
	{
		window.alert("正数");
	}
	else if (n < 0) {
		window.alert("负数");
	}else if (n == 0) {
		window.alert("0");
	}else {
		window.alert("错误");
	}
}