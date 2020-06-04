# nodeManager
nodeManager is a simple app to create, connect and manage nodes.

## Build
You need Qt 5.14 or later, with Qt Creator you can open, build and run `qmake/nodeManager.pro`.
You need a compiler with C++ 17 support.

## Inspiration
nodeManager is based on the QGraphicsView examples from Qt:  
https://doc.qt.io/qt-5/qtwidgets-graphicsview-diagramscene-example.html

## Usage
* add nodes by pressing "Add node"
* in move mode, you can move the nodes around
* in connect mode, you can connect two nodes with a connection
* hold CTRL while scrolling to zoom in and out
* hold CTRL while moving an unselected node to select multiple nodes
* with `File -> Save As` you can persist the current state as JSON document
* with `File -> Open` you can load a persisted file

## Tasks
- [x] create nodes
- [x] connect nodes
- [ ] I/O ports for nodes
- [ ] port compatibility
- [ ] colorized port types
- [ ] arithmetic node ops
- [x] multiple selection
- [x] zoom
- [x] persistence

## Todos
- [ ] unit tests
- [ ] full deployment (sign,notarize)
- [ ] translations
