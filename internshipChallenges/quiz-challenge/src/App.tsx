// Future Updates/Features
// Persist the selected options when we visit a previously answered Quiz

import React, { useEffect, useState } from "react";
import { Quiz } from "./components";

import { TQuizData, TResult } from "./Types";
import { QuizData } from "./temp/dummyData";

const App: React.FC = () => {
    const [quizIndex, setQuizIndex] = useState(0);
    const [currentQuiz, setCurrentQuiz] = useState<TQuizData>(QuizData[0]);
    const [quizResult, setQuizResult] = useState<TResult>({});
    const [isQuizCompleted, setIsQuizCompleted] = useState(false);

    const isFirst = quizIndex === 0;
    const isLast = quizIndex === QuizData.length - 1;

    const handleNextQuiz = () => {
        if (quizIndex < QuizData.length - 1) setQuizIndex((prev) => prev + 1);
    };

    const handlePrevQuiz = () => {
        if (quizIndex > 0) setQuizIndex((prev) => prev - 1);
    };

    const handleSubmit = (currentResults: TResult) => {
        setIsQuizCompleted(true);
        console.log("Final Result:" + JSON.stringify(currentResults, null, 2));
    };

    useEffect(() => {
        setCurrentQuiz(QuizData[quizIndex]);
        console.log(quizResult);
    }, [quizIndex]);

    return (
        <>
            <h1>
                <b>QUIZ CHALLENGE</b>
            </h1>
            <hr />
            <br />
            <Quiz
                key={currentQuiz.id}
                {...currentQuiz}
                isFirst={isFirst}
                isLast={isLast}
                next={handleNextQuiz}
                prev={handlePrevQuiz}
                submit={handleSubmit}
                setQuizAnswers={setQuizResult}
            />
            {isQuizCompleted && (
                <div>
                    <h2>Quiz Completed!</h2>
                    <h3>Results:</h3>
                    <ul>
                        {Object.entries(quizResult).map(([key, value]) => (
                            <li key={key}>
                                Quiz {key}: {value}
                            </li>
                        ))}
                    </ul>
                    <p>Thank you for participating!</p>
                </div>
            )}
            <br />
        </>
    );
};

export default App;
