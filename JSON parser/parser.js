const fs = require("node:fs");

const test1 = "./tests/step2/valid.json";
const test2 = "./tests/step2/invalid.json";

const isValid = (json) => {
  if (json.length == 0) {
    throw new Error("Not a valid JSON");
  }
  if (json[0] !== "{") throw new Error("Needs an opening bracket");
  if (json[json.length - 2] !== "}")
    throw new Error("Needs an closing bracket");
  console.log(json);
};

try {
  const data = fs.readFileSync(test1, "utf8");
  isValid(data);
} catch (err) {
  console.error(err);
}
