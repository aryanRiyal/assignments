const getUserData = async function (count) {
    const API = `https://randomuser.me/api/?page=${count}&results=1&seed=abc`;
    const response = await fetch(API);
    if (!response.ok) {
        throw new Error("Failed to fetch user data");
    }
    const data = await response.json();
    console.log("fetching current user data: " + JSON.stringify(data.results, null, 1));
    return data.results[0];
};

export default getUserData;
