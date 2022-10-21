import { useEffect, useState } from "react";
import "./App.css";
import { MAX_DISTANCE, MODULE_IP } from "./constants";
import Cost from "./Cost";

function App() {
  const [heights, setHeights] = useState([]);
  const [totalDiff, setTotalDiff] = useState(null);

  useEffect(() => {
    let currentDiff = totalDiff;

    const intervalID = setInterval(async () => {
      const newDistance = await getHeight();
      const temp = heights.length === 0 ? [] : [...heights];
      temp.push(newDistance);
      setHeights([...temp]);

      const diff = heights.at(-2) - heights.at(-1);
      if (diff > 0) {
        currentDiff += diff;
        setTotalDiff(currentDiff);
      }
    }, 5000);
    return () => clearInterval(intervalID);
  }, [heights, totalDiff]);

  useEffect(() => {}, [heights, totalDiff]);

  const value = Math.abs(100 - (heights.at(-1) / MAX_DISTANCE) * 100);
  const percent = value > 100 ? 0 : value;
  const time = new Date().toLocaleTimeString();

  return (
    <div className='App'>
      <h1>Water Level</h1>
      {heights.at(-1) !== null ? (
        <>
          <div className='container'>
            <div className='wrapper'>
              <div className='box' style={{ height: `${percent}%` }}></div>
            </div>
            <div className='dashboard'>
              <h4>Currently at</h4>
              <h1>{percent.toFixed(2)}%</h1>
              <h4>capacity</h4>
              <span className='rule' />
              <h4 className='update'>Last updated {time}</h4>
            </div>
          </div>
          <div className='history'>
            <h2>Cost</h2>
            <Cost totalDiff={totalDiff} />
          </div>
        </>
      ) : null}
    </div>
  );
}

export default App;

export const getHeight = async () => {
  const res = await fetch(`http://${MODULE_IP}/`);
  const json = await res.json();
  if (json.distance > 100) {
    return 100;
  } else {
    return json.distance || 0;
  }
};
