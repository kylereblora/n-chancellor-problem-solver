import React, {Component} from 'react';
import { solver } from './solver'
 
class App extends Component {
    state = {
        content: '',
        solutions: []
    }

    handleRead = (e) => {
        this.setState({content: e.target.result}, () => {
            /*let solutions =*/ solver(this.state.content)
            // this.setState({solutions})
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
            </div>
        );
    }
}

export default App;