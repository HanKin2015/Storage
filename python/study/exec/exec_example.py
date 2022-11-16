def exec_example():
    exec('aa = 45')
    print(aa)
    logger.info(aa)
    
    age = 'age_hj'
    exec('{} = 23'.format(age))
    logger.info(age_hj)
    
    cols = ['a']
    for col in cols:
        exec('{}_li = []'.format(col))
    col = 'b'
    exec('{}_li = []'.format(col))
    logger.info('{}_li = []'.format(col))
    logger.info(b_li)
    logger.info(a_li)
    
def debug():
    """debug测试
    """
    
    cols = ['a']
    num = 233
    for col in cols:
        exec('{}_li = num'.format(col), globals())
    #exec('a_li.append({})'.format(num), globals())
    logger.info(a_li)