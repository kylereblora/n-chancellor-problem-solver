import React, {Component} from 'react';

class App extends Component {
    state = {

    }

    handleRead = (e) => {
        console.log(e.target.result);
        
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