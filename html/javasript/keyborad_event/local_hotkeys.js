import hotkeys from 'hotkeys-js';

hotkeys('f5', function(event, handler) {
  // Prevent the default refresh event under WINDOWS system
  event.preventDefault();
  alert('you pressed F5!');
});

// Returning false stops the event and prevents default browser events
// Mac OS system defines `command + r` as a refresh shortcut
hotkeys('ctrl+r, command+r', function() {
  alert('stopped reload!');
  return false;
});

// Single key
hotkeys('a', function(event,handler){
  //event.srcElement: input 
  //event.target: input
  if(event.target === "input"){
      alert('you pressed a!')
  }
  alert('you pressed a!') 
});

// Key Combination
hotkeys('ctrl+a,ctrl+b,r,f', function (event, handler){
  switch (handler.key) {
    case 'ctrl+a': alert('you pressed ctrl+a!');
      break;
    case 'ctrl+b': alert('you pressed ctrl+b!');
      break;
    case 'r': alert('you pressed r!');
      break;
    case 'f': alert('you pressed f!');
      break;
    default: alert(event);
  }
});

hotkeys('ctrl+a+s', function() {
    alert('you pressed ctrl+a+s!');
});

// Using a scope
hotkeys('*','wcj', function(event){
  console.log('do something', event);
});