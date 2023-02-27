/**
 * @api {Get} /user/get getUserInfo1
 * @apiGroup User
 *
 * @apiParam {String} name 文章名
 * @apiParamExample {json} Request-Example
 * {
 *  "userName": "Eve"
 * }
 *
 * @apiSuccessExample  {json} Response-Example
 * {
 *   "userName": "Eve",
 *   "createTime": "1568901681"
 *   "updateTime": "1568901681"
 * }
 */
function getUserInfo1(username) {
  // 假如这个函数是根据用户名返回用户信息的
}

/**
 * @api {方法} 路径 getUserInfo2
 * @apiGroup Group
 * @apiDescription 描述这个API的信息
 *
 * @apiParam {String} userName 用户名
 * @apiParamExample {json} request-example
 * {
 *  "userName": "Eve"
 * }
 *
 * @apiError {String} message 错误信息
 * @apiErrorExample  {json} error-example
 * {
 *   "message": "用户名不存在"
 * }
 * 
 * 
 * @apiSuccess {String} userName 用户名
 * @apiSuccess {String} createTime 创建时间
 * @apiSuccess {String} updateTime 更新时间
 * @apiSuccessExample  {json} success-example
 * {
 *   "userName": "Eve",
 *   "createTime": "1568901681"
 *   "updateTime": "1568901681"
 * }
 */
function getUserInfo2(username) {
  // 假如这个函数是根据用户名返回用户信息的
}

/**
 * @api {方法} 路径 getUserInfo3
 * @apiGroup Group
 * @apiDescription 描述这个API的信息
 *
 * @apiParam {String} userName 用户名
 * @apiParamExample {json} request-example
 * {
 *  "userName": "Eve"
 * }
 *
 * @apiError {String} message 错误信息
 * @apiErrorExample  {json} error-example
 * {
 *   "message": "用户名不存在"
 * }
 * 
 * 
 * @apiSuccess {String} userName 用户名
 * @apiUse Time
 * @apiSuccessExample  {json} success-example
 * {
 *   "userName": "Eve",
 *   "createTime": "1568901681"
 *   "updateTime": "1568901681"
 * }
 */
function getUserInfo3(username) {
  // 假如这个函数是根据用户名返回用户信息的
}
