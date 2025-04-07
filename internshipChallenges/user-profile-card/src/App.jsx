import React, { useEffect, useState } from "react";
import { ProfileCard, Pagination, getUserData } from "./components";

const App = () => {
    const [count, setCount] = useState(1);
    const [user, setUser] = useState(null);

    useEffect(() => {
        getUserData(count)
            .then((data) => setUser(data))
            .catch((error) => console.error("Error fetching user:", error));
    }, [count]);

    if (!user) {
        return <div className="text-center text-lg mt-10">Loading...</div>;
    }

    const next = function () {
        if (count >= 30) {
            console.warn("Page is the last Page!");
        } else {
            setCount(count + 1);
        }
    };

    const prev = function () {
        if (count <= 1) {
            console.warn("No data before page number 1!");
        } else {
            setCount(count - 1);
        }
    };

    return (
        <div className="flex flex-col items-center justify-center min-h-screen bg-gradient-to-r from-indigo-500 via-purple-500 to-pink-500">
            <ProfileCard user={user} />
            <Pagination count={count} next={next} prev={prev} />
        </div>
    );
};

export default App;
