export type TQuizData = {
    id: number;
    type: "single" | "multiple";
    question: string;
    options: string[];
    correctAnswers: string[];
};

export type TResult = Record<number, string>;

export type TQuizProps = {
    id: number;
    type: "single" | "multiple";
    question: string;
    options: string[];
    correctAnswers: string[];
    isFirst: boolean;
    isLast: boolean;
    next: () => void;
    prev: () => void;
    submit: (results: TResult) => void;
    setQuizAnswers: React.Dispatch<React.SetStateAction<TResult>>;
};
