import json  
import ujson  

def monkey_patch_json():  
    json.__name__ = 'ujson'  
    json.dumps = ujson.dumps  
    json.loads = ujson.loads  

monkey_patch_json()
