import React from "react";
import { crossSectionalArea, ratePerLitre } from "./constants";

const Cost = ({ totalDiff }) => {
  const totalWaterUsedInLitres = (totalDiff * crossSectionalArea) / 1000;
  const totalCost = totalWaterUsedInLitres * ratePerLitre;

  return (
    <table>
      <thead>
        <tr>
          <th>Total Water Used</th>
          <th>Total Cost</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>{totalWaterUsedInLitres} Litres</td>
          <td>&#x20b9; {totalCost}</td>
        </tr>
      </tbody>
    </table>
  );
};

export default Cost;
