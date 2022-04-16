import { useEffect, useState } from "react";
import { getHeight } from "./getHeight";

function App() {
  const [heights, setHeights] = useState([]);

  useEffect(() => {
    console.log(heights);
  }, [heights]);

  useEffect(() => {
    const intervalID = setInterval(async () => {
      const temp = await getHeight();
      const tempArray = [...heights];
      tempArray.push(temp);
      setHeights(tempArray);
    }, 5000);
    return () => clearInterval(intervalID);
  });
  return <div className='App'>Hello World</div>;
}

export default App;
