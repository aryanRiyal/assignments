import { useEffect, useState } from "react";
import { TQuizProps } from "../Types";

export default function Quiz({
    id,
    type,
    question,
    options,
    correctAnswers,
    isFirst,
    isLast,
    next,
    prev,
    submit,
    setQuizAnswers
}: TQuizProps) {
    const [selectedSingleValue, setSelectedSingleValue] = useState("");
    const [selectedMultiValue, setSelectedMultiValue] = useState<string[]>([]);

    useEffect(() => {
        setSelectedSingleValue("");
        setSelectedMultiValue([]);
    }, [id]);

    const handleRadioChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        setSelectedSingleValue(e.target.value);
    };

    const handleCheckboxChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        const { value, checked } = e.target;

        setSelectedMultiValue((prev) => (checked ? [...prev, value] : prev.filter((item) => item !== value)));
    };

    const handleAction = () => {
        const PASS = "PASS";
        const FAIL = "FAIL";
        let resultStatus = FAIL;

        if (type === "single") {
            resultStatus = correctAnswers[0] === selectedSingleValue ? PASS : FAIL;
        } else {
            const allMatch =
                correctAnswers.length === selectedMultiValue.length &&
                correctAnswers.every((ans) => selectedMultiValue.includes(ans));
            resultStatus = allMatch ? PASS : FAIL;
        }

        setQuizAnswers((prev) => {
            const newResults = { ...prev, [id]: resultStatus };
            if (isLast) {
                submit(newResults);
            }
            return newResults;
        });

        if (!isLast) next();
    };

    return (
        <div>
            <h1>Quiz Number: {id}</h1>
            <h2>{question}</h2>
            {type === "single"
                ? options.map((option, idx) => (
                      <label key={idx} style={{ display: "block" }}>
                          <input
                              type="radio"
                              value={option}
                              checked={selectedSingleValue === `${option}`}
                              onChange={handleRadioChange}
                          />
                          {option}
                      </label>
                  ))
                : options.map((option, idx) => (
                      <label key={idx} style={{ display: "block" }}>
                          <input
                              type="checkbox"
                              value={option}
                              checked={selectedMultiValue.includes(option)}
                              onChange={handleCheckboxChange}
                          />
                          {option}
                      </label>
                  ))}
            <br />
            <br />
            <p>
                Selected Value{type === "multiple" ? "s" : ""}:&nbsp;
                {type === "multiple" ? selectedMultiValue.join(", ") : selectedSingleValue}
            </p>
            <div>
                <br />
                {isFirst ? "First Quiz" : <button onClick={prev}>&lt; Prev Quiz</button>}
                {" | "}
                <button onClick={handleAction}>{isLast ? "< Submit >" : "Next Quiz >"}</button>
            </div>
        </div>
    );
}
