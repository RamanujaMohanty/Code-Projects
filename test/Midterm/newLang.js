function checkLang(newArray)
{
        var checkedArray = newArray.filter((obj[key]) => obj[key] >= 85);
        return checkedArray;
}
const languages = [
        {name: "a", score: 95},
        {name: "b", score: 90},
        {name: "c", score: 75},
        {name: "d", score: 85},
        {name: "e", score: 70}
];
const popLang = checkLang(languages);
console.log(popLang);
