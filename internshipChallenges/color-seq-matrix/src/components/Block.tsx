type TBlock = {
    isGreen: boolean;
    isOrange: boolean;
    handleClick: () => void;
};

export const Block = ({ isGreen, isOrange, handleClick }: TBlock) => {
    let bgColorAndBorder = "bg-neutral-950 border-neutral-400";
    if (isGreen) bgColorAndBorder = "bg-green-500 border-neutral-800";
    if (isOrange) bgColorAndBorder = "bg-orange-500 border-neutral-800";
    return <div className={`border cursor-pointer col-span-1 h-40 ${bgColorAndBorder}`} onClick={handleClick}></div>;
};
