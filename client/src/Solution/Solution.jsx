import React from 'react'
import './solution.css';

function zeros(dimensions) {
    var array = [];

    for (var i = 0; i < dimensions[0]; ++i) {
        array.push(dimensions.length == 1 ? 0 : zeros(dimensions.slice(1)));
    }

    return array;
}


const Solution = (props) => {
    const {specificSolution} = props;
    console.log(specificSolution);
    
    let size = specificSolution.length;
    let tempArray = zeros([size, size]);
    
    
    specificSolution.forEach(element => {
        let x = parseInt(element / size)
        let y = parseInt(element % size)

        tempArray[x][y] = 1
    });

    console.log(tempArray);
        

    return (
        <table align="center" className="table">
            {
                tempArray.map((row, i) => {
                    return (
                        <tr key={i}>
                            {
                                row.map((col, j) => {
                                    
                                    if (col === 1) return (
                                        <td key={j} className="chancyBlock"></td>
                                    )

                                    else return (
                                        <td key={j} className="regularBlock"></td>
                                    )

                                    
                                })
                            }
                        </tr>
                    )
                })
            }
        </table>
    )
}

export default Solution