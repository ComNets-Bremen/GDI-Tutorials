/*
 *   To the extent possible under law, Leonard Göhrs
 *  has waived all copyright and related or neighboring
 *            rights to boring-landslide.
 *
 *        This work is published from: Germany.
 */

'use strict';

var config = {
  'keys' : {
    'up'   : ['ArrowLeft', 'ArrowUp', 'PageUp', 'Backspace'],
    'down' : ['ArrowRight', 'ArrowDown', 'PageDown', ' '],
    'home' : ['Home'],
    'end'  : ['End']
  }
}

function currentSlide()
{
  var hash= window.location.hash;

  var curSlide= hash.startsWith('#slide_') ?
      Number(hash.split('_')[1]) : 1;

  return (curSlide);
}

function changeSlideAbs(slideNum)
{
  var newID = 'slide_' + slideNum;

  if (document.getElementById(newID)) {
    window.location.hash= '#' + newID;

    return (true);
  }
  else {
    return (false);
  }
}

function changeSlideRel(rel)
{
  return (changeSlideAbs(currentSlide() + rel));
}

function install()
{
  var body= document.getElementsByTagName('body')[0];

  /* Install mousewheel Hooks.
   * The lower one is a hack for Firefox */
  body.addEventListener('mousewheel',
                        d => changeSlideRel(d.deltaY > 0 ? 1 : -1),
                        false);

  body.addEventListener('DOMMouseScroll',
                        d => changeSlideRel(d.detail > 0 ? 1 : -1),
                        false);


  body.addEventListener('keyup',
                        k => {
                          if (config.keys.up.includes(k.key)) changeSlideRel(-1);
                          if (config.keys.down.includes(k.key)) changeSlideRel(1);
                          if (config.keys.home.includes(k.key)) changeSlideAbs(1);
                          if (config.keys.end.includes(k.key)) changeSlideAbs(lastSlide);
                        },
                        false);
}
