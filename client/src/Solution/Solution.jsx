import React from 'react'

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
        <div>
            {
                tempArray.map((row, i) => {
                    return (
                        <div key={i}>
                            {
                                row.map((col, j) => {
                                    return (
                                        <span key={j}>{col}</span>
                                    )
                                })
                            }
                        </div>
                    )
                })
            }
        </div>
    )
}

export default Solution