const prompt = require("prompt");

prompt.start();

prompt.get(["red", "blue", "rrows", "brows"], function (err, result) {
	if (err) {
		return onErr(err);
	}
	// result.rrows *= 6;
	// result.brows *= 6;
	console.log(`${result.red, result.blue, result.rrows, result.brows}`)
	let redScore = result.red + result.rrows;
	let blueScore = result.blue + result.brows;
	let finalScore = redScore - blueScore + 63;
	console.log({redScore, blueScore})

	// console.log("Balls Scored:");
	// console.log("  Red Balls Scored: " + result.red);
	// console.log("  Blue Balls Scored: " + result.blue);
	// console.log("  Red Rows Scored: " + result.rrows);
	// console.log("  Blue Rows Scored: " + result.brows);

	console.log("\nFinal Score: " + finalScore);
});

function onErr(err) {
	console.log(err);
	return 1;
}
