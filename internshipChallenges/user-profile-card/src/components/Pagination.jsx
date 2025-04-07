import React from "react";

function Pagination({ count, next, prev }) {
    return (
        <div className="text-center mt-4">
            <div className="text-lg font-semibold mb-2">Page: {count}</div>

            <button
                onClick={prev}
                className="bg-pink-500 ml-1 mr-2 px-4 py-2 text-white rounded-md hover:bg-red-700 cursor-pointer"
            >
                Previous
            </button>
            <button
                onClick={next}
                className="bg-indigo-500 ml-2 mr-1 px-4 py-2 text-white rounded-md hover:bg-indigo-700 cursor-pointer"
            >
                Next
            </button>
        </div>
    );
}

export default Pagination;
