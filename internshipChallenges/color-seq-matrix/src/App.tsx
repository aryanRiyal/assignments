import { useState } from "react";
import { Block } from "./components/Block";

type TMatrixSize = 2 | 3 | 4 | 5;

function App() {
    const [clickedOrder, setClickedOrder] = useState<number[]>([]);
    const [orangeBlocks, setOrangeBlocks] = useState<Set<number>>(new Set());
    const [orderOfMatrix, setOrderOfMatrix] = useState<TMatrixSize>(3);
    const [totalBlocks, setTotalBlocks] = useState<number>(orderOfMatrix * orderOfMatrix);

    const handleClick = (index: number) => {
        if (clickedOrder.includes(index) && !orangeBlocks.has(index)) return;
        console.log("Clicked block:", index + 1);

        const newOrder = [...clickedOrder, index];
        setClickedOrder(newOrder);

        if (index === totalBlocks - 1) {
            console.log("Last Block clicked changing colors to orange...");
            const greenOnly = newOrder.filter((idx) => !orangeBlocks.has(idx));
            greenOnly.forEach((blockIndex, i) => {
                setTimeout(() => {
                    setOrangeBlocks((prev) => {
                        const newSet = new Set(prev);
                        newSet.add(blockIndex);
                        return newSet;
                    });
                }, i * 250);
            });
        }
    };

    const handleMatrixOrderChange = (e: React.ChangeEvent<HTMLSelectElement>) => {
        console.log("Changing Matrix size!");
        const MatrixSize: TMatrixSize = Number(e.target.value) as TMatrixSize;
        setOrderOfMatrix(MatrixSize);
        setTotalBlocks(MatrixSize * MatrixSize);
        refresh();
    };

    const refresh = () => {
        console.log("...Resetting the Matrix...");
        setClickedOrder([]);
        setOrangeBlocks(new Set());
    };

    const gridColsMapping: Record<TMatrixSize, string> = {
        2: "grid-cols-2",
        3: "grid-cols-3",
        4: "grid-cols-4",
        5: "grid-cols-5"
    };

    const widthMapping: Record<TMatrixSize, string> = {
        2: "w-1/3",
        3: "w-2/5",
        4: "w-3/5",
        5: "w-4/5"
    };

    const gridColsClass = gridColsMapping[orderOfMatrix];
    const widthClass = widthMapping[orderOfMatrix];

    return (
        <div className="flex flex-col items-center justify-center w-full min-h-screen gap-1 bg-neutral-800">
            <div className="flex flex-col w-2/5 gap-3">
                <h1 className="text-5xl font-medium text-center text-white">Color Sequence Matrix</h1>
                <div className="flex justify-between w-full gap-2">
                    <select
                        name="matrixType"
                        value={orderOfMatrix}
                        onChange={handleMatrixOrderChange}
                        className="w-1/4 p-1 text-lg text-white bg-black rounded-md outline-none cursor-pointer"
                    >
                        <option value="2">2x2</option>
                        <option value="3">3x3</option>
                        <option value="4">4x4</option>
                        <option value="5">5x5</option>
                    </select>
                    <button className="text-2xl underline cursor-pointer text-neutral-300" onClick={refresh}>
                        Refresh
                    </button>
                </div>
            </div>
            <div className={`grid ${widthClass} ${gridColsClass} text-white border-2 border-neutral-600`}>
                {Array(orderOfMatrix * orderOfMatrix)
                    .fill(null)
                    .map((_, index: number) => (
                        <Block
                            key={index}
                            isGreen={clickedOrder.includes(index)}
                            isOrange={orangeBlocks.has(index)}
                            handleClick={() => handleClick(index)}
                        />
                    ))}
            </div>
        </div>
    );
}

export default App;
