function deleteKey(obj, key)
{
        if (key in obj)
        {
                delete obj[key];
        }
        else
        {
                throw new Error("Key does not exist in the object.");
        }
}

const obj = {name: "Alice", age: 25};
deleteKey(obj, "name");
console.log(obj);
