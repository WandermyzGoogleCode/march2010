<?php
/**
 * Smarty plugin
 * @package Smarty
 * @subpackage plugins
 */


/**
 * Smarty truncate modifier plugin
 *
 * Type:     modifier<br>
 * Name:     truncate<br>
 * Purpose:  Truncate a string to a certain length if necessary,
 *           optionally splitting in the middle of a word, and
 *           appending the $etc string or inserting $etc into the middle.
 * @link http://smarty.php.net/manual/en/language.modifier.truncate.php
 *          truncate (Smarty online manual)
 * @author   Monte Ohrt <monte at ohrt dot com>
 * @param string
 * @param integer
 * @param string
 * @param boolean
 * @param boolean
 * @return string
 */
function smarty_modifier_truncate($string, $length = 80, $etc = '...',
                                  $break_words = false, $middle = false)
{
    if ($length == 0)
        return '';

    if (strlen($string) > $length) {
        $length -= min($length, strlen($etc));
        if (!$break_words && !$middle) {
            $string = preg_replace('/\s+?(\S+)?$/', '', substr($string, 0, $length+1));
        }
        if(!$middle) {
            //return substr($string, 0, $length) . $etc;
            $result = substr($string, 0, $length) . $etc;
        } else {
            //return substr($string, 0, $length/2) . $etc . substr($string, -$length/2);
            $result = substr($string, 0, $length/2) . $etc . substr($string, -$length/2);
        }
        
        //TODO SpaceFlyer: 处理$result
        //以下是GBK的
        /*
        //Added by SpaceFlyer, to avoid ? in the title
						$good = true;
						for($i=0; $i<strlen($result); $i++)
						{
							if (!$good)
							{
								$good = true;
								continue;
							}
							if (ord($result[$i]) >= 128)
								$good = false;
						}
						if (!$good)
							$result = substr($result, 0, strlen($result)-1);
		//End
        */
        return $result;
    } else {
        return $string;
    }
}

/* vim: set expandtab: */

?>
