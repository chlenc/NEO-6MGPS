import React from 'react';
import './App.css';
import {Map, YMaps, Placemark} from 'react-yandex-maps';

import Dialog  from 'rc-dialog';
import 'rc-dialog/assets/index.css';

const geoData = require('./data.json');

class App extends React.Component {
    state = {
        isOpenDialog: false,
        dialogTitle: 'test',
        dialogContent: '',
    };

    handleOpenDialog = (title, content) => {
        this.setState({
            isOpenDialog: true,
            dialogTitle: title,
            dialogContent: content
        })
    };

    handleCloseDialog = () => {
        this.setState({isOpenDialog: false})
    };

    render() {
        const {isOpenDialog, dialogTitle, dialogContent} = this.state;
        return <div className="App">
            <YMaps>
                <Map
                    width={'100%'}
                    height={800}
                    defaultState={{center: [geoData[0].lat, geoData[0].lng], zoom: 15}}>
                    {geoData.map(({lat, lng, data}, i) =>
                        <Placemark key={i} geometry={[lat, lng]} onClick={() => this.handleOpenDialog(data, data)}/>)
                    }
                </Map>
            </YMaps>
            <Dialog
                title={dialogTitle}
                onClose={this.handleCloseDialog}
                visible={isOpenDialog}
            >
                <p>{dialogContent}</p>
            </Dialog>
        </div>
    }
}

export default App
