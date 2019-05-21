import React from 'react'
// import './solution.css'
// import { Grid, Segment } from 'semantic-ui-react'

const Solution = (props) => {
    const {sol} = props;
    let tempArray = Array(sol.length * sol.length).fill(0)

    sol.forEach(element => {
        tempArray[element] = 1
    });

    console.log(tempArray);
    

    return (
        <div>
            {

            }
        </div>
    )
}

export default Solution