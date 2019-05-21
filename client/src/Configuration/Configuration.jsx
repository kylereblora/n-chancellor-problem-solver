import React from 'react'
import Solution from '../Solution/Solution';
// import './solution.css'
// import { Grid, Segment } from 'semantic-ui-react'

const Configuration = (props) => {
    const {solutionSet} = props;
    console.log(solutionSet);
    

    return (
        <div>
            {
                solutionSet && solutionSet.length > 0 ?

                solutionSet.map((solution,index) => {
                    return (
                        <div key={index}>
                            <Solution specificSolution={solution} />
                        </div>
                    )
                })

                :

                <p>No solution available.</p>
            }
        </div>
    )
}

export default Configuration