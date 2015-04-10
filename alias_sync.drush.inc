<?php

/**
 * @file
 * Syncs aliases.
 */

/**
 * Implements hook_drush_command().
 */
function alias_sync_drush_command() {
  $items['alias-sync'] = array(
    'description' => dt('Links drush aliases in your file system to your local drush path. Why? Facilitates distributed alias files.'),
    'arguments' => array(
      'path' => dt('The path of a directory to search. Defaults at /var/www.'),
    ),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
 return $items;
}


/**
 * Syncs drushrc.php files in a given file system.
 */
function drush_alias_sync($path = NULL) {
  $path = $path ? $path : '/var/www';
  drush_log("Syncing files", 'ok');
  $files = findFiles("/var/www", 'drush', "drushrc.php");
  $drush_dir = "/home/" . exec('whoami') . '/.drush';
  foreach ($files as $file) {
    drush_shell_cd_and_exec($drush_dir, "ln -s {$file} .");
  }
  drush_log("Synced " . count($files) . " files", 'ok');
}

/**
 * Finds files in a file system.
 */
function findFiles($base_dir, $asset_dir, $extension) {
  function glob_recursive($base_dir, &$directories = array()) {
    foreach(glob($base_dir, GLOB_ONLYDIR | GLOB_NOSORT) as $folder) {
      $directories[] = $folder;
      glob_recursive("{$folder}/*", $directories);
    }
  }
  glob_recursive($base_dir, $directories);
  $files = array();
  foreach ($directories as $base_dir) {
    if (strpos($base_dir, $asset_dir) != FALSE) {
      foreach (glob("{$base_dir}/*.{$extension}") as $file) {
        $files[] = $file;
      }
    }
  }
  return $files;
}
