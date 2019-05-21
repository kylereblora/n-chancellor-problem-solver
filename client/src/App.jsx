import React, {Component} from 'react';
import { solver } from './solver'
import Configuration from './Configuration/Configuration'

class App extends Component {
    state = {
        content: '',
        solutions: []
    }

    handleRead = (e) => {
        this.setState({content: e.target.result}, () => {
            let solutions = solver(this.state.content)
            this.setState({solutions})
        });
        
    }

    handleFileChange = (e) => {
            const file = e.target.files[0];
            let reader = new FileReader();
            reader.onload = this.handleRead;
            reader.readAsText(file);
       
    }


    render() {

        return(
            <div>
                <input type="file" accept=".in" onChange={this.handleFileChange}/>
                <div>
                    {
                        this.state.solutions.solution && this.state.solutions.solution.length > 0 ?

                        <div>
                            {
                                this.state.solutions.solution.map((sol, index) => {
                                   return (
                                    <div key={index}>
                                        <p>Configuration #{index+1}</p>
                                        <Configuration solutionSet={sol} />
                                        {/* <p>{sol}</p> */}
                                    </div>
                                   )
                                })
                            }
                        </div>

                        :

                        <p>Upload a configuration.</p>
                    }
                </div>
            </div>
        );
    }
}

export default App;