var judgeDateTime = function (tmp) {
  return tmp < 10 ? ('0' + tmp) : tmp
}

// 将Date对象转为字符串
export function getDateTime (dateTime) {
  const year = dateTime.getFullYear()
  let month = dateTime.getMonth() + 1
  let day = dateTime.getDate()
  let hour = dateTime.getHours()
  let minute = dateTime.getMinutes()
  let second = dateTime.getSeconds()
  month = judgeDateTime(month)
  day = judgeDateTime(day)
  hour = judgeDateTime(hour)
  minute = judgeDateTime(minute)
  second = judgeDateTime(second)
  const date = year + '-' + month + '-' + day
  const time = hour + ':' + minute + ':' + second
  return date + ' ' + time
}

// 将日期时间字符串改变其呈现内容
export function transTime (dateTime) {
  const tmpDateTime = new Date(dateTime)
  // console.log('tmpTime: ' + tmpDateTime)
  const curDateTime = new Date()
  // console.log('curTime: ' + curDateTime)
  const cur = curDateTime.getTime()
  // console.log('cur:' + cur)
  const tmp = tmpDateTime.getTime()
  // console.log('tmp:' + tmp)
  let gap = (cur - tmp) / 1000
  // console.log('gap:' + gap)
  if (gap > 60 * 60 * 24) { // 间隔大于24h
    return dateTime.substr(5)
  } else if (gap > 60 * 60) { // 间隔大于1h
    gap = Math.floor(gap / (60 * 60))
    return gap + '小时前'
  } else if (gap > 60) { // 间隔大于一分钟
    gap = Math.floor(gap / (60))
    return gap + '分钟前'
  } else {
    return '刚刚'
  }
}

// 呈现数量转换——大于10000时显示1w或者1.xw
export function transNumber (number) {
  let tmp = number
  if (tmp > 10000) { // 大于1w
    if (tmp % 10000 === 0) {
      tmp = tmp / 10000 + 'w'
    } else {
      tmp = tmp / 10000
      tmp = Math.floor(tmp * 100) / 100 + 'w'
    }
  }
  return tmp
}
