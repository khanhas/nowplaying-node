const { readdirSync, statSync } = require("fs");

const reducer = (f, o) => o.reduce((a, b) => a || f.endsWith(b), false)

function listDirRecur(dir, endsWithOpt) {
	readdirSync(dir)
		.forEach(f => {
			const curf = dir + '/' + f;
			if (statSync(curf).isDirectory()) {
				listDirRecur(curf, endsWithOpt);
			} else {
				if (reducer(f, endsWithOpt)) {
					console.log(curf);
				}
			}
		})
}

function listDir(dir, endsWithOpt) {
	readdirSync(dir)
		.filter(f => reducer(f, endsWithOpt))
		.forEach(f => console.log(dir + '/' + f))
}

listDirRecur('src/SDKs', [".cpp", ".c", ".h"]);
listDirRecur('src/taglib', [".h"]);
listDir("src", [".h",".cpp"])