import { TQuizData } from "../Types";

export const QuizData: TQuizData[] = [
    {
        id: 1,
        type: "single", // 'single' for single-choice
        question: "What is the capital of Germany?",
        options: ["Berlin", "Munich", "Hamburg", "Frankfurt"],
        correctAnswers: ["Berlin"]
    },
    {
        id: 2,
        type: "multiple", // 'multiple' for multiple-choice
        question: "Which of the following are programming languages?",
        options: ["HTML", "Python", "JavaScript", "CSS"],
        correctAnswers: ["Python", "JavaScript"]
    },
    {
        id: 3,
        type: "single",
        question: "React is developed and maintained by which company?",
        options: ["Google", "Facebook", "Microsoft", "Amazon"],
        correctAnswers: ["Facebook"]
    },
    {
        id: 4,
        type: "multiple",
        question: "Which tools are part of a typical React development workflow?",
        options: ["Webpack", "Babel", "Photoshop", "ESLint"],
        correctAnswers: ["Webpack", "Babel", "ESLint"]
    }
];
