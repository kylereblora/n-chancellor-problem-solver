import React from 'react'
import Solution from '../Solution/Solution';
import './configuration.css'
// import { Grid, Segment } from 'semantic-ui-react'



class Configuration extends React.Component {
    state = {
        solutionSet: this.props.solutionSet,
        activeIndex: 0,
    }

    handlePrevSolution = () => {
        const {solutionSet, activeIndex} = this.state;
        const newPointer = activeIndex === 0 ? solutionSet.length -1 : activeIndex - 1;
        this.setState({activeIndex: newPointer});
    }

    handleNextSolution = () => {
        const {solutionSet, activeIndex} = this.state;
        const newPointer = activeIndex === solutionSet.length-1 ? 0 : activeIndex + 1;
        this.setState({activeIndex: newPointer});
    }

    render() {
        const {solutionSet, activeIndex} = this.state;
        console.log(solutionSet);
        
    
        return (
            <div className="config">
                {
                    solutionSet && solutionSet.length > 0 ?
    
                    <div>
                        <div className="configBoard">
                            <div className="control" id="left">
                                <button className="prev" onClick={this.handlePrevSolution}>&#10094;</button>
                            </div>
                            <Solution specificSolution={solutionSet[activeIndex]} />
                            <div className="control" id="right">
                                <button className="next" onClick={this.handleNextSolution}>&#10095;</button>
                            </div>
                        </div>
                        <div>
                            <p>Solution {activeIndex+1} of {solutionSet.length}</p>
                        </div>
                        {/* <div className="controls">
                            <button className="prev" onClick={this.handlePrevSolution}>&#10094;</button>
                            <button className="next" onClick={this.handleNextSolution}>&#10095;</button>
                        </div> */}
                        
                    </div>
    
                    :
    
                    <p>No solution available.</p>
                }
            </div>
        )
    }
}

export default Configuration